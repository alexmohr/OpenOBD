import * as autobahn from "autobahn";
import { PidQuery } from "./PidQuery";
import { ServiceQuery } from "./ServiceQuery";
import { setUrlPath } from '../utils/common'

export class Communication {
    ////
    // Private fields
    ////

    /**
     * URL where the vidar router is found.
     */
    private readonly _url = "ws://" + top.location.hostname + ":55555/ws";

    /**
     * WAMP realm.
     */
    private readonly _realm = "openobd";

    private _session?: autobahn.Session;

    private _isOpen: boolean = false;

    private _pidSubscribers: Map<string, Array<(pidQuery: PidQuery) => any>>;

    public constructor() {
        this._pidSubscribers = new Map<string, Array<(pidQuery: PidQuery) => any>>();
    }


    /**
     * Opens the wamp connection
     */
    public open(): void {
        var connection = new autobahn.Connection({ url: this._url, realm: this._realm });
        connection.onopen = (session: autobahn.Session) => this.connectionOpened(session);
        connection.open();

    }

    public isOpen(): boolean {
        return this._isOpen;
    }

    public getPidData(serviceId: number, pidName: string): When.Promise<PidQuery> | null {
        if (this._session == undefined) {
            return null;
        }

        return this._session.call("get.service." + serviceId + "." + pidName).then(this.parsePidQuery)
    }

    public getServiceData(serviceId: number): When.Promise<ServiceQuery> | null {
        if (this._session == undefined) {
            return null;
        }

        return this._session.call("get.service." + serviceId.toString()).then(this.parseServiceQuery)
    }

    public subscribeToPid(serviceId: number, pidName: string, handler: (pidQuery: PidQuery) => any): void {
        if (this._session == undefined) {
            return;
        }

        let url = "get.service." + serviceId + "." + pidName + ".subscribe";
        this._session.call(url);
        let subs = this._pidSubscribers.get(pidName);
        if (subs == undefined) {
            subs = new Array<(pidQuery: PidQuery) => any>()
            this._pidSubscribers.set(pidName, subs);
        }

        subs.push(handler);
    }

    public unsubscribeFromPid(serviceId: number, pidName: string): void {
        if (this._session == undefined) {
            return;
        }

        let url = "get.service." + serviceId + "." + pidName + ".unsubscribe";
        this._session.call(url);
        this._pidSubscribers.set(pidName,  new Array<(pidQuery: PidQuery) => any>());
    }

    public setUpdateRate(updateRateMs: number){
        if (this._session == undefined) {
            return;
        }

        let url = "set.service.any.setUpdateRate";
        this._session.call(url, [updateRateMs]).done();
    }

    private initSubscriptions(): void {
        if (this._session == undefined) {
            return;
        }

        let url = "get.service.any.subscriptions";
        this._session.subscribe(url, (data) => {
            for (let i = 0; i < data.length; i++) {
                let pidData = this.parsePidQuery(data[i]);
                let pidName = pidData.getPid().getName();
                let subs = this._pidSubscribers.get(pidName);
                if (undefined == subs) {
                    continue;
                }

                for (let sub in subs) {
                    subs[sub](pidData);
                }
            }
        });
    }

    public clearSubscriptions(): void {
        if (this._session == undefined) {
            return;
        }

        this._session.call("set.service.any.clearPidSubscriptions").done();
    }


    public verifyLoaded(): void {
        if (!this.isOpen()) {
            setUrlPath("");
        }

        this.clearSubscriptions();
    }

    private parsePidQuery(result: any): PidQuery {
        return PidQuery.deserialize(result);
    }

    private parseServiceQuery(result: any): ServiceQuery {
        return ServiceQuery.deserialize(result);
    }

    private connectionOpened = (session: autobahn.Session): void => {
        this._session = session;
        this._isOpen = true;
        this.initSubscriptions()
    }
}