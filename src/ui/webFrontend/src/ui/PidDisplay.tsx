import * as React from 'react';
import { PidQuery } from '../wamp/PidQuery';
import TextField from '@material-ui/core/TextField';
import Paper from '@material-ui/core/Paper';
import { stateStore } from '../redux/reducer'
import { Request, DisplayType } from './request';
import Typography from '@material-ui/core/Typography';
import DeleteIcon from '@material-ui/icons/Delete';
import IconButton from '@material-ui/core/IconButton';



import Button from '@material-ui/core/Button';
import Dialog from '@material-ui/core/Dialog';
import DialogActions from '@material-ui/core/DialogActions';
import DialogContent from '@material-ui/core/DialogContent';
import DialogContentText from '@material-ui/core/DialogContentText';
import DialogTitle from '@material-ui/core/DialogTitle';

import CircularProgress from '@material-ui/core/CircularProgress';
import { Theme } from '@material-ui/core/styles/createMuiTheme';
import createStyles from '@material-ui/core/styles/createStyles';
import withStyles, { WithStyles } from '@material-ui/core/styles/withStyles';
import withRoot from '../withRoot';

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
    },

  });


type State = {
  retryDialogOpen: boolean;
  connectionReady: boolean;
};

interface Props extends WithStyles<typeof styles> {
  pidQuery: PidQuery;
  request: Request | null;
  removeCallback: ((request: Request | null) => any) | null;
}

export class PidDisplay extends React.Component<Props, State> {

  render() {
    let pidQuery = this.props.pidQuery;
    let dataMember = pidQuery.getData().getDataMember();
    let fields: JSX.Element[] = new Array<JSX.Element>();
    let pidName = pidQuery.getPid().getName();
    dataMember.forEach(dm => {
      let key = pidName + pidQuery.getPid().getId() + dm.getName();
      fields.push(
        <TextField
          className={stateStore.getState().commonStyles.textField}
          key={key}
          label={dm.getName()}
          value={dm.getNumberValue()}
          helperText={"Unit: " + dm.getUnit()}
          margin="normal"
          InputProps={{ readOnly: true }} />)
    })

    let paperKey;
    let iconButton = null;
    let request = this.props.request;
    if (request !=null && this.props.removeCallback != null) {
      paperKey = request.key;
      iconButton = <IconButton aria-label="Delete"
        onClick={() => {
          if (this.props.removeCallback != null){
            this.props.removeCallback(request)
          }}}
        className={stateStore.getState().commonStyles.closeButton}>
        <DeleteIcon fontSize="small" />
      </IconButton>
    } else {
      paperKey = pidName + pidQuery.getPid().getId();
    }

    let paper = <Paper key={paperKey} elevation={1} className={this.props.classes.paper}>
      <Typography variant="h5" gutterBottom>
        {pidQuery.getPid().getDescription()}
        {iconButton}
      </Typography>
      {fields}
    </Paper>

    return paper;
  }
}

export default withRoot(withStyles(styles)(PidDisplay));