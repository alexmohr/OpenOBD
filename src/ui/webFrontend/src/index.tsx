import * as React from 'react';
import * as ReactDOM from 'react-dom';
import Loader from './pages/loader';
import Dashboard from './pages/dashboard';
import Overview from './pages/overview';

import {
  BrowserRouter as Router,Route,Link,Switch} from 'react-router-dom'
import overview from './pages/overview';

//ReactDOM.render(<Index />, document.querySelector('#root'));
ReactDOM.render(
    <Router>
        <Switch>
            <Route exact path='/' component={Loader} />
            <Route exact path='/dashboard' component={Dashboard} />
            <Route exact path='/overview' component={Overview} />
            Overview
        </Switch>
    </Router>,
    document.querySelector('#root'));