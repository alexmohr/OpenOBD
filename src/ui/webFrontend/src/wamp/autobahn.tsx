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

    public constructor() {
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
        let url = "get.service." + serviceId + "." + pidName;
        this._session.call(url + ".subscribe");
        this._session.subscribe(url, (data) => {
            let pidData = this.parsePidQuery(data[0]);
        });
    }

    public clearSubscriptions(): void {
        if (this._session == undefined) {
            return;
        }

        this._session.call("set.clearSubscriptions").done();
    }


    public verifyLoaded(): void {
        if (!this.isOpen()) {
            setUrlPath("");
        }
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
    }
}