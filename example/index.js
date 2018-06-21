import React from 'react';
import {AppRegistry} from 'react-native';

import {app} from './App.bs.js';

console.ignoredYellowBox = ['Warning: component'];

AppRegistry.registerComponent('ReasonDemo', () => app);
