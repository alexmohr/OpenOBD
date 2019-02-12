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

    public getPidData(pidName: string): When.Promise<PidQuery> | null {
        if (this._session == undefined) {
            return null;
        }

        return this._session.call("get.service.1." + pidName).then(this.parsePidQuery)
    }

    public getServiceData(serviceId: number): When.Promise<ServiceQuery> | null {
        if (this._session == undefined) {
            return null;
        }

        return this._session.call("get.service." + serviceId.toString()).then(this.parseServiceQuery)
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