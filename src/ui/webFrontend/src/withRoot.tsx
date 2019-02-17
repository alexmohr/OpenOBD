import * as React from 'react';
import { MuiThemeProvider, createMuiTheme } from '@material-ui/core/styles';
import purple from '@material-ui/core/colors/purple';
import green from '@material-ui/core/colors/green';
import CssBaseline from '@material-ui/core/CssBaseline';
import ResponsiveDrawer from './pages/appdrawer'

// A theme with custom primary and secondary color.
// It's optional.
const theme = createMuiTheme({
  palette: {
   type: "dark"
  },
  typography: {
    useNextVariants: true,
  },

});

function withRoot<P>(Component: React.ComponentType<P>) {
  function WithRoot(props: P) {
    // MuiThemeProvider makes the theme available down the React tree
    // thanks to React context.
    return (
      <MuiThemeProvider theme={theme}>
        {/* CssBaseline kickstart an elegant, consistent, and simple baseline to build upon. */}
        <CssBaseline />
        <ResponsiveDrawer>
          <Component {...props} />
        </ResponsiveDrawer>
      </MuiThemeProvider>
    );
  }

  return WithRoot;
}

export default withRoot;
