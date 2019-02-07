import { Communication } from '../wamp/autobahn'

export type Action = {
    type: 'INIT',
} | {
    type: 'LOADED',
    value: boolean
}


export const init = (): Action => ({
    type: 'INIT'
})

export const loaded = (): Action => ({
    type: 'LOADED',
    value: true
})
