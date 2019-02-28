import * as React from 'react';
import { PidQuery } from '../wamp/PidQuery';
import { Request, DisplayType } from '../ui/request';
import { PidDisplay } from '../ui/PidDisplay';
import { Theme } from '@material-ui/core/styles/createMuiTheme';
import createStyles from '@material-ui/core/styles/createStyles';
import withStyles, { WithStyles } from '@material-ui/core/styles/withStyles';
import withRoot from '../withRoot';
import { stateStore } from '../redux/reducer'
import Grid from '@material-ui/core/Grid';
import Fab from '@material-ui/core/Fab';
import AddIcon from '@material-ui/icons/Add';
import Button from '@material-ui/core/Button';
import Dialog from '@material-ui/core/Dialog';
import DialogActions from '@material-ui/core/DialogActions';
import DialogContent from '@material-ui/core/DialogContent';
import DialogTitle from '@material-ui/core/DialogTitle';
import withMobileDialog from '@material-ui/core/withMobileDialog';
import  {getObject, setObject} from '../redux/localStorage';
import { TSMap } from "typescript-map"

const styles = (theme: Theme) =>
  createStyles({
    root: {
      flexGrow: 1
    },
    fabButton: {
      marginTop: theme.spacing.unit * 4,
      marginRight: theme.spacing.unit * 2
    },
    addButton:{
      textTransform: "none"
    },
    textField: {
      marginLeft: theme.spacing.unit,
      marginRight: theme.spacing.unit,
      width: 200,
    },
    paper: {
      padding: theme.spacing.unit,
      paddingTop: theme.spacing.unit * 2,
      paddingBottom: theme.spacing.unit * 2,
      margin: theme.spacing.unit
    },
    closeButton: {
      marginLeft: theme.spacing.unit * 3,
    },
    loaderRoot: {
      textAlign: 'center',
      paddingTop: theme.spacing.unit * 20,
    },
    progress: {
      margin: theme.spacing.unit * 2,
    }

  });


type State = {
  open: boolean;
  elements: TSMap<string, JSX.Element>;
  requestList: TSMap<string, Request>
  blackList: TSMap<string, string>
};


class Dashboard extends React.Component<WithStyles<typeof styles>, State> {
  private availablePids = new Array<Request>();
  private static readonly requestListName = "requestList"
  private static readonly blackListName = "blackList";
  state = {
    open: false,
    elements: new TSMap<string, JSX.Element>(),
    requestList: Dashboard.createOrLoadRequestList(),    
    blackList: Dashboard.createOrLoadBlacklist(),
  };

  private static createOrLoadRequestList(): TSMap<string, Request> {
    let jVal = getObject(this.requestListName);
    let val = new TSMap<string, Request>();; 
    if (jVal != null){
      val = val.fromJSON(jVal);
    }

    return val;
  }

  private static createOrLoadBlacklist(): TSMap<string, string> {
    let jVal = getObject(this.blackListName);
    let val = new TSMap<string, string>();; 
    if (jVal != null){
      val = val.fromJSON(jVal);
    }

    return val;
  }

  componentDidMount() {
    stateStore.getState().autobahn.verifyLoaded();
    stateStore.getState().autobahn.setUpdateRate(200);
    
    this.load();
  }
/*
  http://voidcanvas.com/top-10-react-graph-chart-libraries-with-demo/
  https://whawker.github.io/react-jsx-highcharts/examples/Gauge/index.html
*/
  componentWillUnmount(){
    stateStore.getState().autobahn.clearSubscriptions();
  }

  private load(): void {
    let serviceQuery = stateStore.getState().autobahn.getServiceData(1);
    if (null != serviceQuery) {
      serviceQuery.done((sq) => {
        for (let pidName of sq.getPidNames()) {
          this.availablePids.push(new Request(1, pidName, DisplayType.TextField))
        }
      })
    }

    this.processRequestList(this.state.requestList, this.state.blackList);
  }

  private processRequestList(requestList: TSMap<string, Request>, blackList: TSMap<string, string>) {
    requestList.forEach((value: Request) => {
      if (blackList.get(value.key) == undefined) {
        let pidQuery = stateStore.getState().autobahn.getPidData(value.serviceId, value.pidName);
        if (null != pidQuery) {
          pidQuery.done((pq) => {
            this.processPidQuery(value, pq);
            stateStore.getState().autobahn.subscribeToPid(value.serviceId, value.pidName, (result) => {
              this.processPidQuery(value, result);
            });
          });
        }
      }
    });
  }

  private processPidQuery(request: Request, pidQuery: PidQuery): JSX.Element {
    let paper = <PidDisplay classes={this.props.classes} request={request} removeCallback={(rq)=> {this.handleRemove(rq)}} pidQuery={pidQuery}/>
    let elements = this.state.elements;
    elements.set(request.key, paper);
    this.setState({
      elements: elements
    });

    return paper;
  }

  handleClickOpen = () => {
    this.setState({ open: true });
  };

  private handleRemove(request: Request | null): void {
    if (null == request){
      return;
    }
    let requests = this.state.requestList;
    let elements = this.state.elements;
    let blackList = this.state.blackList;
    requests.delete(request.key);
    elements.delete(request.key);
    blackList.set(request.key, "");

    this.setState({
      requestList: requests, 
      elements: elements,
      blackList: blackList
    });

    setObject(Dashboard.blackListName, blackList.toJSON())
    setObject(Dashboard.requestListName, requests.toJSON())
    stateStore.getState().autobahn.unsubscribeFromPid(request.serviceId, request.pidName);

    this.processRequestList(requests, blackList);
    this.handleClose();
  }

  private handleAdd(request: Request): void {
    let requests = this.state.requestList;
    let blackList = this.state.blackList;
    requests.set(request.key, request);
    blackList.delete(request.key);

    this.setState({
      requestList: requests, 
      blackList: blackList
    });
  
    setObject(Dashboard.blackListName, blackList.toJSON())
    setObject(Dashboard.requestListName, requests.toJSON())

    this.processRequestList(requests, blackList);
    this.handleClose();
  }


  handleClose = () => {
    this.setState({ open: false });
  };

  render() {
    let elementList = new Array<JSX.Element>();
    this.state.elements.forEach((value: JSX.Element, key: string|undefined) => {
      if (key != undefined && this.state.blackList.get(key) == undefined){
        elementList.push(value)
      }
    });

    let gridKey = 0;
    return <div>
      <Grid container className={this.props.classes.root} spacing={16}>
        <Grid item xs={12}>
          <Grid container spacing={16}>
            {elementList.map(value => (
              <Grid key={gridKey + gridKey++} item>
                {value}
              </Grid>
            ))}
          </Grid>
        </Grid>
      </Grid>
      <Grid container direction="row" justify="flex-end" alignItems="flex-end">
        <Fab onClick={this.handleClickOpen} color="primary" aria-label="Add"
          className={this.props.classes.fabButton}>
          <AddIcon />
        </Fab>
      </Grid>

      <div>

        <Dialog
          fullScreen={true}
          open={this.state.open}
          onClose={this.handleClose}
          aria-labelledby="responsive-dialog-title">
          <DialogTitle id="responsive-dialog-title">{"Add new UI Element"}</DialogTitle>
          <DialogContent>

            {this.availablePids.map(value => (
              <div key={gridKey + gridKey++}> 
                <Button key={gridKey + gridKey++} className={this.props.classes.addButton} onClick={()=>this.handleAdd(value)} >
                  {value.pidName}
                </Button>
              </div>

            ))}
          </DialogContent>
          <DialogActions>
            <Button onClick={this.handleClose} color="secondary">
              Cancel
            </Button>

          </DialogActions>
        </Dialog>
      </div>
    </div>
  }
}

export default withMobileDialog()(withRoot(withStyles(styles)(Dashboard)));
