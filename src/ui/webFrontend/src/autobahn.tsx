import * as autobahn from "autobahn";
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

    private foobar(result :{}) : void{
        console.log(JSON.stringify(result))
    }

    public getServices(): void {
        //this._session.call("service.get.1.VehicleSpeed").catch((error) => this.logWampError(error))
        if (this._session == undefined) {
            return;
        }
        
        this._session.call("get.service.1").then(this.foobar)
        this._session.call("get.service.1.VehicleSpeed").then(this.foobar)

    }

    private connectionOpened = (session: autobahn.Session): void => {
        this._session = session;
        this._isOpen = true;
    }
}