export class DataMember {
    private details: Map<String, String>;
    private numberValue: number;
    private name: string;
    private unit: string;
    private min: number;
    private max: number;
    constructor(details: Map<String, String>, numberValue: number,
        name: string, unit: string, min: number, max: number) {

        this.details = details;
        this.numberValue = numberValue;
        this.name = name;
        this.unit = unit;
        this.min = min;
        this.max = max;
    }

    public static deserialize(input: any): DataMember {
        return new DataMember(input.details, input.numberValue, input.name, input.unit, input.min, input.max)
    }

    public getDetails(): Map<String, String> {
        return this.details;
    }

    public getNumberValue(): number {
        return this.numberValue;
    }

    public getName(): string{
        return this.name;
    }

    public getUnit(): string{
        return this.unit;
    }

    public getMin(): number{
        return this.min;
    }

    public getMax(): number{
        return this.max;
    }
}

export class Data {
    private dataMember: DataMember[];
    public constructor(dataMember: DataMember[]) {
        this.dataMember = dataMember;
    }

    public static deserialize(input: any): Data {
        let members: DataMember[] = new Array<DataMember>();
        for (let i = 0; i < input.length; i++) {
            members.push(DataMember.deserialize(input[i]))
        }
        return new Data(members);
    }

    public getDataMember(): DataMember[] {
        return this.dataMember;
    }
}