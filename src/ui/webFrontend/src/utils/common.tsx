export function setUrlPath(path: string): void {
    window.location.assign(window.location.protocol + '//' + window.location.host + '/#/' + path);
}
