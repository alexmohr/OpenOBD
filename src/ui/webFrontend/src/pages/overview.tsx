import * as React from 'react';

import Typography from '@material-ui/core/Typography';
import { Theme } from '@material-ui/core/styles/createMuiTheme';
import createStyles from '@material-ui/core/styles/createStyles';
import withStyles, { WithStyles } from '@material-ui/core/styles/withStyles';
import withRoot from '../withRoot';
import { stateStore } from '../redux/reducer'
import { CircularProgress } from '@material-ui/core';
import { PidQuery } from '../wamp/PidQuery';
import { PidDisplay } from '../ui/PidDisplay';

const styles = (theme: Theme) =>
  createStyles({
    root: {
      display: 'flex',
      flexWrap: 'wrap',
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
    stateStore.getState().autobahn.setUpdateRate(5000);
    this.initialLoad();
  }

  private processPidQuery(pidQuery: PidQuery): JSX.Element {
    let paper = <PidDisplay classes={this.props.classes} request={null} removeCallback={null} pidQuery={pidQuery}/>
  
    let paperKey = pidQuery.getPid().getName() + pidQuery.getPid().getId();
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
      return <div className={this.props.classes.loaderRoot}>
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
