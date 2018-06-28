/**
 * Copyright (c) 2017-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

// See https://docusaurus.io/docs/site-config.html for all the possible
// site configuration options.

const users = [
  {
    caption: 'User1',
    image: '/test-site/img/docusaurus.svg',
    infoLink: 'https://www.facebook.com',
    pinned: true
  }
];

const siteConfig = {
  title: 'Rebolt Navigation',
  tagline:
    'A fast and declarative navigation library for React Native written in Reason',
  url: 'https://callstack.github.io/rebolt-navigation',
  baseUrl: '/',
  projectName: 'rebolt-navigation',
  organizationName: 'callstack',
  headerLinks: [
    { doc: 'intro', label: 'Docs' },
    { doc: 'api-stack-navigator', label: 'API' }
  ],
  users,
  headerIcon: 'img/logo.png',
  footerIcon: 'img/logo.png',
  favicon: 'img/logo.png',
  colors: { primaryColor: '#3c64a6', secondaryColor: '#525659' },
  copyright: 'Copyright © ' + new Date().getFullYear() + ' Callstack',
  usePrism: ['jsx', 'reason'],
  highlight: {
    theme: 'atom-one-light'
  },
  scripts: ['https://buttons.github.io/buttons.js'],
  onPageNav: 'separate',
  ogImage: 'img/logopng',
  twitterImage: 'img/logopng',
  repoUrl: 'https://github.com/callstackincubator/rebolt-navigation'
};

module.exports = siteConfig;
