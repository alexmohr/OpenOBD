import React from 'react';
import PropTypes from 'prop-types';
import createStyles from '@material-ui/core/styles/createStyles';
import AppBar from '@material-ui/core/AppBar';
import CssBaseline from '@material-ui/core/CssBaseline';
import Divider from '@material-ui/core/Divider';
import SwipeableDrawer from '@material-ui/core/SwipeableDrawer';
import Hidden from '@material-ui/core/Hidden';
import IconButton from '@material-ui/core/IconButton';
import List from '@material-ui/core/List';
import ListItem from '@material-ui/core/ListItem';
import { Theme } from '@material-ui/core/styles/createMuiTheme';
import ListItemIcon from '@material-ui/core/ListItemIcon';
import ListItemText from '@material-ui/core/ListItemText';
import Dashboard from '@material-ui/icons/Dashboard';
import MenuIcon from '@material-ui/icons/Menu';
import Toolbar from '@material-ui/core/Toolbar';
import FormatListBulleted from '@material-ui/icons/FormatListBulleted';
import Warning from '@material-ui/icons/Warning';

import Typography from '@material-ui/core/Typography';
import withStyles, { WithStyles } from '@material-ui/core/styles/withStyles';
import { setUrlPath } from '../utils/common'

const drawerWidth = 240;

const styles = (theme: Theme) =>
    createStyles({
        root: {
            display: 'flex',
            paddingBottom: theme.spacing.unit * 10,
        },
        drawer: {
            [theme.breakpoints.up('sm')]: {
                width: drawerWidth,
                flexShrink: 0,
            },
        },
        appBar: {
            zIndex: theme.zIndex.drawer + 1,
        },
        menuButton: {
        },
        toolbar: theme.mixins.toolbar,
        drawerPaper: {
            width: drawerWidth,
        },
        contentWithMenu: {
            marginLeft: drawerWidth + theme.spacing.unit,
            marginRight: theme.spacing.unit, 
            [theme.breakpoints.down('xs')]: {
                marginLeft: theme.spacing.unit,
            },
        },
        contentWithoutMenu: {
            marginLeft: theme.spacing.unit,
            marginRight: theme.spacing.unit
        },
    });


type State = {
    mobileOpen: boolean,
    desktopOpen: boolean
};


class AppDrawer extends React.Component<WithStyles<typeof styles>, State> {
    state = {
        mobileOpen: false,
        desktopOpen: true
    };

    handleDrawerToggleMobile = () => {
        this.setState(state => ({ mobileOpen: !state.mobileOpen }));
    }

    handleDrawerToggleDesktop = () => {
        this.setState(state => ({ desktopOpen: !state.desktopOpen }));
    };

    render() {
        const drawer = (
            <div>
                <div className={this.props.classes.toolbar} />
                <Divider />
                <List>
                    <ListItem button onClick={() => setUrlPath("Dashboard")}>
                        <ListItemIcon>
                            <Dashboard />
                        </ListItemIcon>
                        <ListItemText primary="Dashboard" />
                    </ListItem>
                    <ListItem button onClick={() => setUrlPath("Overview")}>
                        <ListItemIcon>
                            <FormatListBulleted />
                        </ListItemIcon>
                        <ListItemText primary="Overview" />
                    </ListItem>
                </List>
                <Divider />
                <List>
                    <ListItem button onClick={() => setUrlPath("TroubleCodes")}>
                        <ListItemIcon>
                            <Warning />
                        </ListItemIcon>
                        <ListItemText primary="Trouble Codes" />
                    </ListItem>
                </List>
            </div>

        );

        let drawerClass = ""
        if (this.state.desktopOpen) {
            drawerClass = this.props.classes.drawer
        }

        let drawerOpenClass = this.props.classes.contentWithoutMenu
        if (this.state.desktopOpen) {
            drawerOpenClass = this.props.classes.contentWithMenu
        }

        return (
            <div>
                <div className={this.props.classes.root}>
                    <CssBaseline />
                    <AppBar position="fixed" className={this.props.classes.appBar}>
                        <Toolbar>
                            <Hidden smUp implementation="css">
                                <IconButton
                                    color="inherit"
                                    aria-label="Open drawer"
                                    onClick={this.handleDrawerToggleMobile}
                                    className={this.props.classes.menuButton}>
                                    <MenuIcon />
                                </IconButton>
                            </Hidden>
                            <Hidden xsDown implementation="css">
                                <IconButton
                                    color="inherit"
                                    aria-label="Open drawer"
                                    onClick={this.handleDrawerToggleDesktop}
                                    className={this.props.classes.menuButton}>
                                    <MenuIcon />
                                </IconButton>
                            </Hidden>
                            <Typography variant="h6" color="inherit" noWrap>
                                Open OBD
                        </Typography>
                        </Toolbar>
                    </AppBar>
                    <nav className={drawerClass}>
                        <Hidden smUp implementation="css">
                            <SwipeableDrawer
                                onOpen={this.handleDrawerToggleMobile}
                                onClose={this.handleDrawerToggleMobile}
                                variant="temporary"
                                open={this.state.mobileOpen}
                                classes={{
                                    paper: this.props.classes.drawerPaper,
                                }}>
                                {drawer}
                            </SwipeableDrawer>
                        </Hidden>
                        <Hidden xsDown implementation="css">
                            <SwipeableDrawer
                                onOpen={this.handleDrawerToggleMobile}
                                onClose={this.handleDrawerToggleMobile}
                                classes={{
                                    paper: this.props.classes.drawerPaper,
                                }}
                                variant="persistent"
                                open={this.state.desktopOpen}>
                                {drawer}
                            </SwipeableDrawer>
                        </Hidden>
                    </nav>
                </div>
                <div className={drawerOpenClass}>
                    {this.props.children}
                </div>
            </div>

        );
    }
}

export default (withStyles(styles)(AppDrawer));