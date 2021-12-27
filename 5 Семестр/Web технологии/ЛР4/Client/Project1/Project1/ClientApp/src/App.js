import React, { Component } from 'react';
import { Route } from 'react-router';
import { Layout } from './components/Layout';
import { Home } from './components/Home';
import { Add } from './components/Add';
import { Update } from './components/Update'

import './custom.css'

export default class App extends Component {
  static displayName = App.name;

  render () {
    return (
        <Layout>
            <Route exact path='/' component={Home} />
            <Route path='/Add' component={Add} />
            <Route path='/Update' component={Update} />
        </Layout>
    );
  }
}
