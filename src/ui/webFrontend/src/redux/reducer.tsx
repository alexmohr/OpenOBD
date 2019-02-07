import { createStore, Store as ReduxStore } from 'redux'
import { Communication } from '../wamp/autobahn'
import { Action } from './actions'

/*
import { getObject, setObject } from './localStorage'


const stateCookie: string = "state";*/

export const stateStore: ReduxStore<AppState> = createStore(reducer)
export type AppState = {
    autobahn: Communication;
    test: boolean;
}


const initialState: AppState = {
    test: true,
    autobahn: new Communication()
}

function reducer(state: AppState | undefined, action: Action): AppState {
    if (undefined == state) {
        state = {
            test: true,
            autobahn: new Communication()
        }
    }

    switch (action.type) {
        case 'INIT':
            //   let initCookie = getObject<Store.All>(stateCookie)
            //   if (null == initCookie) {
            //     state = initialState;
            //   } else {
            //     state = initCookie;
            //   }
            //   state.app.loaded = false
            break;

        case 'LOADED':
            //   state.loaded = action.value;
            break;
    }

    return state
}