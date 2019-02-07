export class Data {
    private stringData: string;
    public constructor(stringData: string){
        this.stringData = stringData;
    }

    public static deserialize(input: any): Data{
        return new Data(input.string);
    }

    public getStringData(): string{
        return this.stringData;
    }
}