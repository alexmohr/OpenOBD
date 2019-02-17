import * as React from 'react';
import Button from '@material-ui/core/Button';
import Dialog from '@material-ui/core/Dialog';
import DialogActions from '@material-ui/core/DialogActions';
import DialogContent from '@material-ui/core/DialogContent';
import DialogContentText from '@material-ui/core/DialogContentText';
import DialogTitle from '@material-ui/core/DialogTitle';
import Typography from '@material-ui/core/Typography';
import { Theme } from '@material-ui/core/styles/createMuiTheme';
import createStyles from '@material-ui/core/styles/createStyles';
import withStyles, { WithStyles } from '@material-ui/core/styles/withStyles';
import withRoot from '../withRoot';
import Paper from '@material-ui/core/Paper';
import TextField from '@material-ui/core/TextField';
import { stateStore } from '../redux/reducer'

const styles = (theme: Theme) =>
  createStyles({
    root: {
      textAlign: 'center',
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
  open: boolean;
};

class Dashboard extends React.Component<WithStyles<typeof styles>, State> {

  state = {
    open: false,
  };

  componentDidMount() {
    stateStore.getState().autobahn.verifyLoaded();
  }

  handleClose = () => {
    this.setState({
      open: false,
    });
  };

  handleClick = () => {
    this.setState({
      open: true,
    });
  };

  render() {

   return  <Paper key={"asdaf"} elevation={1} className={this.props.classes.paper}>
      <TextField
          className={this.props.classes.textField}
          key={"asd"}
          label="Vehicle Speed"
          value={0}
          helperText={"Unit: " + "n"}
          margin="normal"
          InputProps={{ readOnly: true }} />
    </Paper>
  
  }
}

export default withRoot(withStyles(styles)(Dashboard));
