import * as React from 'react';
import Button from '@material-ui/core/Button';
import Dialog from '@material-ui/core/Dialog';
import DialogActions from '@material-ui/core/DialogActions';
import DialogContent from '@material-ui/core/DialogContent';
import DialogContentText from '@material-ui/core/DialogContentText';
import TextField from '@material-ui/core/TextField';
import DialogTitle from '@material-ui/core/DialogTitle';
import Typography from '@material-ui/core/Typography';
import { Theme } from '@material-ui/core/styles/createMuiTheme';
import createStyles from '@material-ui/core/styles/createStyles';
import withStyles, { WithStyles } from '@material-ui/core/styles/withStyles';
import withRoot from '../withRoot';
import { Communication } from '../wamp/autobahn';
import { stateStore } from '../redux/reducer'
import Paper from '@material-ui/core/Paper';
import { loadavg } from 'os';
import { element } from 'prop-types';
import { CircularProgress } from '@material-ui/core';
import { PidQuery } from '../wamp/PidQuery';

const styles = (theme: Theme) =>
  createStyles({
    root: {
      display: 'flex',
      flexWrap: 'wrap',
    },
    loaderDiv: {
      textAlign: 'center',
      paddingTop: theme.spacing.unit * 10,
    },
    progress: {
      margin: theme.spacing.unit * 2,
    },
    paper: {
      padding: theme.spacing.unit,
      paddingTop: theme.spacing.unit * 2,
      paddingBottom: theme.spacing.unit * 2,
      margin: theme.spacing.unit
    },
    textField: {
      marginLeft: theme.spacing.unit,
      marginRight: theme.spacing.unit,
      width: 200,
    },
  });

type State = {
  loadingDone: boolean;
  trigger: boolean;
  elements: Map<string, JSX.Element>;
};

class Overview extends React.Component<WithStyles<typeof styles>, State> {
  state = {
    loadingDone: false,
    trigger: false,
    elements: new Map<string, JSX.Element>()
  };

  componentDidMount() {
    stateStore.getState().autobahn.verifyLoaded();
    this.initialLoad();
  }

  private processPidQuery(pidQuery: PidQuery): JSX.Element {
    let dataMember = pidQuery.getData().getDataMember();
    let fields: JSX.Element[] = new Array<JSX.Element>();
    let pidName = pidQuery.getPid().getName();

    dataMember.forEach(dm => {
      let key = pidName + pidQuery.getPid().getId() + dm.getName();
      fields.push(
        <TextField
          className={this.props.classes.textField}
          key={key}
          label={dm.getName()}
          value={dm.getNumberValue()}
          helperText={"Unit: " + dm.getUnit()}
          margin="normal"
          InputProps={{ readOnly: true }} />)
    })

    let paperKey = pidName + pidQuery.getPid().getId();
    let paper = <Paper key={paperKey} elevation={1} className={this.props.classes.paper}>
      <Typography variant="h5" gutterBottom>
        {pidQuery.getPid().getDescription()}
      </Typography>
      {fields}
    </Paper>

    let elements = this.state.elements;
    elements.set(paperKey, paper);

    this.setState({
      elements: elements
    });

    return paper;
  }


  private initialLoad(): void {
    let serviceQuery = stateStore.getState().autobahn.getServiceData(1);
    if (null == serviceQuery) return;

    serviceQuery.done((sq) => {
      for (let pidName of sq.getPidNames()) {
        let pidQuery = stateStore.getState().autobahn.getPidData(1, pidName);
        if (null == pidQuery)
          continue;
          
        pidQuery.done((pq) => {
          this.processPidQuery(pq)
          stateStore.getState().autobahn.subscribeToPid(1, pidName, (result) => {
            this.processPidQuery(result)
            this.setState({ trigger: !this.state.trigger })
          });

          this.setState({ loadingDone: true });
        });
      }

    })
  }

  render() {
    if (!this.state.loadingDone) {
      return <div className={this.props.classes.loaderDiv}>
        <CircularProgress className={this.props.classes.progress} disableShrink={true}>
          <Typography variant="h4" gutterBottom>
            Loading
          </Typography>
        </CircularProgress>
      </div>
    }

    let elementList = new Array<JSX.Element>();
    this.state.elements.forEach((value: JSX.Element, key: string) => {
      elementList.push(value)
    });
    

    return (
      <div className={this.props.classes.root}>
        <div>
          {
             elementList
          }
        </div>
      </div>
    );
  }
}

export default withRoot(withStyles(styles)(Overview));
