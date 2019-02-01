import * as React from 'react';
import * as ReactDOM from 'react-dom';
import Loader from './pages/loader';
import Dashboard from './pages/dashboard';
import {
  BrowserRouter as Router,Route,Link,Switch} from 'react-router-dom'

//ReactDOM.render(<Index />, document.querySelector('#root'));
ReactDOM.render(
    <Router>
        <Switch>
            <Route exact path='/' component={Loader} />
            <Route exact path='/dashboard' component={Dashboard} />
        </Switch>
    </Router>,
    document.querySelector('#root'));