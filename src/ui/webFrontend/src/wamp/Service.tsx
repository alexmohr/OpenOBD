export class Service {
    private id: number;
    public constructor(id: number){
        this.id = id;
    }
    
    public static deserialize(input: any): Service{
        return new Service(input.id);
    }
}