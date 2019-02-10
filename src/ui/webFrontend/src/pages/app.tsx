import React from 'react';
import PropTypes from 'prop-types';
import createStyles from '@material-ui/core/styles/createStyles';
import AppBar from '@material-ui/core/AppBar';
import CssBaseline from '@material-ui/core/CssBaseline';
import Divider from '@material-ui/core/Divider';
import SwipeableDrawer from '@material-ui/core/SwipeableDrawer';
import Hidden from '@material-ui/core/Hidden';
import IconButton from '@material-ui/core/IconButton';
import InboxIcon from '@material-ui/icons/MoveToInbox';
import List from '@material-ui/core/List';
import ListItem from '@material-ui/core/ListItem';
import { Theme } from '@material-ui/core/styles/createMuiTheme';
import ListItemIcon from '@material-ui/core/ListItemIcon';
import ListItemText from '@material-ui/core/ListItemText';
import MailIcon from '@material-ui/icons/Mail';
import MenuIcon from '@material-ui/icons/Menu';
import Toolbar from '@material-ui/core/Toolbar';
import Typography from '@material-ui/core/Typography';
import withStyles, { WithStyles } from '@material-ui/core/styles/withStyles';
import withRoot from '../withRoot';

const drawerWidth = 240;

const styles = (theme: Theme) =>
    createStyles({
        root: {
            display: 'flex',
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
        content: {
            flexGrow: 1,
            padding: theme.spacing.unit * 3,
        },
    });


type State = {
    mobileOpen: boolean,
    desktopOpen: boolean
};


class ResponsiveDrawer extends React.Component<WithStyles<typeof styles>, State> {
    state = {
        mobileOpen: false,
        desktopOpen: true
    };

    handleDrawerToggleMobile = () => {
        this.setState(state => ({ mobileOpen: !state.mobileOpen }));
    };

    handleDrawerToggleDesktop = () => {
        this.setState(state => ({ desktopOpen: !state.desktopOpen }));
    };

    render() {

        const drawer = (
            <div>
                <div className={this.props.classes.toolbar} />
                <Divider />
                <List>
                    {['Inbox', 'Starred', 'Send email', 'Drafts'].map((text, index) => (
                        <ListItem button key={text}>
                            <ListItemIcon>{index % 2 === 0 ? <InboxIcon /> : <MailIcon />}</ListItemIcon>
                            <ListItemText primary={text} />
                        </ListItem>
                    ))}
                </List>
            </div>
        );

        let drawerClass = ""
        if (this.state.desktopOpen){
            drawerClass = this.props.classes.drawer
        }

        return (
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
                            Responsive drawer
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
                <main className={this.props.classes.content}>
                    <div className={this.props.classes.toolbar} />
                    <Typography paragraph>
                        Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor
                        incididunt ut labore et dolore magna aliqua. Rhoncus dolor purus non enim praesent
                        elementum facilisis leo vel. Risus at ultrices mi tempus imperdiet. Semper risus in
                        hendrerit gravida rutrum quisque non tellus. Convallis convallis tellus id interdum
                        velit laoreet id donec ultrices. Odio morbi quis commodo odio aenean sed adipiscing.
                        Amet nisl suscipit adipiscing bibendum est ultricies integer quis. Cursus euismod quis
                        viverra nibh cras. Metus vulputate eu scelerisque felis imperdiet proin fermentum leo.
                        Mauris commodo quis imperdiet massa tincidunt. Cras tincidunt lobortis feugiat vivamus
                        at augue. At augue eget arcu dictum varius duis at consectetur lorem. Velit sed
                        ullamcorper morbi tincidunt. Lorem donec massa sapien faucibus et molestie ac.
          </Typography>
                    <Typography paragraph>
                        Consequat mauris nunc congue nisi vitae suscipit. Fringilla est ullamcorper eget nulla
                        facilisi etiam dignissim diam. Pulvinar elementum integer enim neque volutpat ac
                        tincidunt. Ornare suspendisse sed nisi lacus sed viverra tellus. Purus sit amet volutpat
                        consequat mauris. Elementum eu facilisis sed odio morbi. Euismod lacinia at quis risus
                        sed vulputate odio. Morbi tincidunt ornare massa eget egestas purus viverra accumsan in.
                        In hendrerit gravida rutrum quisque non tellus orci ac. Pellentesque nec nam aliquam sem
                        et tortor. Habitant morbi tristique senectus et. Adipiscing elit duis tristique
                        sollicitudin nibh sit. Ornare aenean euismod elementum nisi quis eleifend. Commodo
                        viverra maecenas accumsan lacus vel facilisis. Nulla posuere sollicitudin aliquam
                        ultrices sagittis orci a.
          </Typography>
                </main>
            </div>
        );
    }
}

export default withRoot(withStyles(styles)(ResponsiveDrawer));