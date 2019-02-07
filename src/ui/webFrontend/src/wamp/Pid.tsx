export class Pid {

    private id: number;
    private name: string;
    private description: string;
    private minValues: number[];
    private maxValues: number[];
    private units: string[];
    private dataFields: number;

    public constructor(
        id: number, name: string, description: string, minValues: number[], maxValues: number[], units: string[], dataFields: number) {
        this.id = id;
        this.name = name;
        this.description = description;
        this.minValues = minValues;
        this.maxValues = maxValues;
        this.units = units;
        this.dataFields = dataFields;
    }

    public static deserialize(input: any): Pid {
        return new Pid(
            input.id,
            input.name,
            input.description,
            input.minValues,
            input.maxValues,
            input.units,
            input.dataFields);
    }

    public getId(): number{
        return this.id;
    }
    
    public getName(): string{
        return this.name;
    }
    
    public getDescription(): string{
        return this.description;
    }
    
    public getMinValues(): number[]{
        return this.minValues;
    }
    
    public getMaxValues(): number[]{
        return this.maxValues;
    }
    
    public getUnits(): string[]{
        return this.units;
    }
    
    public getDataFields(): number{
        return this.dataFields;
    }
    
}