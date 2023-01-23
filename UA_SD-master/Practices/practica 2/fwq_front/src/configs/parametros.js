const APIENGINE = process.env.REACT_APP_APIENGINE;
const REQUESTTIME = Number(process.env.REACT_APP_REQUESTTIME) * 1000;


console.log({ config: { APIENGINE, REQUESTTIME } });

export { APIENGINE, REQUESTTIME };