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
      marginLeft: 240 + theme.spacing.unit
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
  valueMap: Map<string, number>;
};

class Overview extends React.Component<WithStyles<typeof styles>, State> {
  private elements: JSX.Element[] = new Array<JSX.Element>();
  private paperKeyIndex: number = 0;

  state = {
    loadingDone: false,
    valueMap: new Map<string, number>()
  };

  componentDidMount() {
    stateStore.getState().autobahn.verifyLoaded();
    this.load();
  }

  private processPidQuery(pidQuery: PidQuery): void {
    let dataMember = pidQuery.getData().getDataMember();
    let fields: JSX.Element[] = new Array<JSX.Element>();
    let pidName = pidQuery.getPid().getName();


    dataMember.forEach(dm => {
      let key = pidName + pidQuery.getPid().getId() + dm.getName();
      this.state.valueMap.set(key, dm.getNumberValue())

      fields.push(
        <TextField
          className={this.props.classes.textField}
          key={key}
          label={dm.getName()}
          defaultValue={this.state.valueMap.get(key)}
          helperText={"Unit: " + dm.getUnit()}
          margin="normal"
          InputProps={{ readOnly: true }} />)
    })

    stateStore.getState().autobahn.subscribeToPid(1, pidName, (result) => {
      let map = this.state.valueMap;
      result.getData().getDataMember().forEach(dm => {
        let key = pidName + pidQuery.getPid().getId() + dm.getName();
        let entry = map.get(key);
        if (undefined != entry) {
          map.set(key, dm.getNumberValue());
        }
      });
      this.setState({valueMap: map})
    });

    this.elements.push(
      <Paper key={pidName + this.paperKeyIndex++ + pidQuery.getPid().getId()} elevation={1} className={this.props.classes.paper}>
        <Typography variant="h5" gutterBottom>
          {pidQuery.getPid().getDescription()}
        </Typography>
        {fields}
      </Paper>)
  }


  private load(): void {
    let serviceQuery = stateStore.getState().autobahn.getServiceData(1);
    if (null == serviceQuery) return;

    serviceQuery.done((sq) => {
      for (let pidName of sq.getPidNames()) {
        let pidQuery = stateStore.getState().autobahn.getPidData(1, pidName);
        if (null == pidQuery) 
          continue;

        pidQuery.done((pq) => { 
          this.processPidQuery(pq);

          this.setState({
            loadingDone: true,
          });
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


    return (
      <div className={this.props.classes.root}>
        <div>
          {this.elements}
        </div>
      </div>
    );
  }
}

export default withRoot(withStyles(styles)(Overview));
