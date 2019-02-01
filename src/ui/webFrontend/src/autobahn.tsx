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

    private static _instance: Communication | null = null;

    public constructor() {
        Communication._instance = this;
    }


    public static getInstance() : Communication{
        if (null == Communication._instance ){
            Communication._instance = new Communication();
        }
        return Communication._instance;
    }

   
    /**
     * Opens the wamp connection
     */
    public open(): void {
        var connection = new autobahn.Connection({ url: this._url, realm: this._realm });
        connection.onopen = (session: autobahn.Session) => this.connectionOpened(session);
        connection.open();
        
    }

    public isOpen(): boolean{
        return this._isOpen;
    }

    private connectionOpened = (session: autobahn.Session): void => {
        this._session = session;
        this._isOpen = true;
    }
}