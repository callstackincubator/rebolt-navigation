import React from 'react';
import { AppRegistry } from 'react-native';

import { app } from './App.bs.js';

console.ignoredYellowBox = ['Warning: component', 'Warning: isMounted'];

AppRegistry.registerComponent('ReasonDemo', () => app);