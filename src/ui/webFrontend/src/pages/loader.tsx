import * as React from 'react';
import Button from '@material-ui/core/Button';
import Dialog from '@material-ui/core/Dialog';
import DialogActions from '@material-ui/core/DialogActions';
import DialogContent from '@material-ui/core/DialogContent';
import DialogContentText from '@material-ui/core/DialogContentText';
import DialogTitle from '@material-ui/core/DialogTitle';

import CircularProgress from '@material-ui/core/CircularProgress';
import Typography from '@material-ui/core/Typography';
import { Theme } from '@material-ui/core/styles/createMuiTheme';
import createStyles from '@material-ui/core/styles/createStyles';
import withStyles, { WithStyles } from '@material-ui/core/styles/withStyles';
import withRoot from '../withRoot';
import { Redirect } from 'react-router-dom'
import { stateStore } from '../redux/reducer'

const styles = (theme: Theme) =>
  createStyles({
    root: {
      textAlign: 'center',
      paddingTop: theme.spacing.unit * 20,
    },
    progress: {
      margin: theme.spacing.unit * 2,
    },
  });

type State = {
  retryDialogOpen: boolean;
  connectionReady: boolean;
};

class Loader extends React.Component<WithStyles<typeof styles>, State> {
  private _connectTimeoutMs: number = 5000;


  state = {
    retryDialogOpen: false,
    open: false,
    connectionReady: false
  };

  private initVehicle() : void{
    //stateStore.getState().autobahn.getServices();
  }

  private waitForConnection(connectionOpenRequestTime: Date): void {
    setTimeout(() => {
      let elapsedTime = new Date().valueOf() - connectionOpenRequestTime.valueOf();
      if (stateStore.getState().autobahn.isOpen()) {
        this.initVehicle();
        this.setState({
          connectionReady: true,
        });
        return;
      }

      if (elapsedTime < this._connectTimeoutMs) {
        this.waitForConnection(connectionOpenRequestTime);
        return;
      }

      this.setState({
        retryDialogOpen: true,
      });


    }, 50);
  }

  private openConnection(): void {
    stateStore.getState().autobahn.open();

    let connectionOpenRequestTime = new Date();
    this.waitForConnection(connectionOpenRequestTime);

  };

  componentDidMount() {
    this.openConnection();
  }

  private handleRetry() : void {
    this.setState({
      retryDialogOpen: false,
    });
    this.openConnection();
  };


  render() {
    if (stateStore.getState().autobahn.isOpen()) {
      return <Redirect to='Dashboard' />
    }

    return (
      <div className={this.props.classes.root}>
        <CircularProgress className={this.props.classes.progress} />
        <Typography variant="h4" gutterBottom>
          Loading
        </Typography>


        <Dialog open={this.state.retryDialogOpen} onClose={this.handleRetry}>
          <DialogTitle>Connection failure</DialogTitle>
          <DialogContent>
            <DialogContentText>Failed to connect to backend.</DialogContentText>
          </DialogContent>
          <DialogActions>
            <Button color="primary" onClick={this.handleRetry}>
              Retry
            </Button>
          </DialogActions>
        </Dialog>

      </div>
    );
  }
}

export default withRoot(withStyles(styles)(Loader));
