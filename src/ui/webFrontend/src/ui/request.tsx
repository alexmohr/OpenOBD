export class Request {
    public readonly serviceId: number;
    public readonly pidName: string;
    public readonly type: DisplayType;
    public readonly key: string;

    constructor(serviceId: number, pidName: string, type: DisplayType) {
        this.serviceId = serviceId;
        this.pidName = pidName;
        this.type = type;
        this.key = this.serviceId.toString() + this.pidName + this.type;
    }
}

export enum DisplayType {
    TextField,
    Gauge,
}
