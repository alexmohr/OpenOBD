export class ServiceQuery {
    private pidNames: string[];
    public constructor(pidNames: string[]) {
        this.pidNames = pidNames;
    }

    static deserialize(input: any): ServiceQuery {
        return new ServiceQuery(input.pids)
    }

    public getPidNames(): string[] {
        return this.pidNames;
    }
}