// simple storage helper

export function setObject<T>(name: string, value: T) {
    if (value == undefined || value == null) {
        return;
    }

    localStorage.setItem(name, JSON.stringify(value))
}

export function getObject<T>(cname: string): T | null {
    let item = localStorage.getItem(cname);
    if (null == item)
        return null;
    let obj = JSON.parse(item)
    let cast = obj as T;

    if (null == cast) {
        cast = {} as T;;
    }

    return cast
}
