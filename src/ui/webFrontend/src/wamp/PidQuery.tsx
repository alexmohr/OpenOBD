import { Data } from './Data'
import { Pid } from './Pid'
import { Service } from './Service'
export class PidQuery {
    private data: Data;
    private pid: Pid;
    private service: Service;

    public constructor(data: Data, pid: Pid, service: Service) {
        this.data = data;
        this.pid = pid;
        this.service = service;
    }

    static deserialize(input: any): PidQuery {
        return new PidQuery(
            Data.deserialize(input.data),
            Pid.deserialize(input.pid),
            Service.deserialize(input.service));
    }

    public getData(): Data{
        return this.data;
    }
    
    public getPid(): Pid{
        return this.pid;
    }
    
    public getService(): Service{
        return this.service;
    }
    
}