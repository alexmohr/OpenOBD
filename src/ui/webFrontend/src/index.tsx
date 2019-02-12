import * as React from 'react';
import * as ReactDOM from 'react-dom';
import Loader from './pages/loader';
import Dashboard from './pages/dashboard';
import Overview from './pages/overview';

import {
  HashRouter as Router,Route,Link,Switch} from 'react-router-dom'

//ReactDOM.render(<Index />, document.querySelector('#root'));
ReactDOM.render(
    <Router>
        <Switch>
            <Route exact path='/' component={Loader} />
            <Route exact path='/Dashboard' component={Dashboard} />
            <Route exact path='/Overview' component={Overview} />
            Overview
        </Switch>
    </Router>,
    document.querySelector('#root'));