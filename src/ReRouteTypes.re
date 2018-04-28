module type Config = {
  type route;
  let stateForUrl: (array(route), string) => array(route);
};