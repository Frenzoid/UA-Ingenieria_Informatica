import io from "socket.io-client";
import encrypt from "socket.io-encrypt";

import { REGISTRYADDRESS, KAFKACONTROLLER, SECRET } from "./parametros";

const socketRegistry = io(REGISTRYADDRESS, { timeout: 1000, rejectUnauthorized: false });
const kafkaWebSocket = io(KAFKACONTROLLER, { timeout: 1000, rejectUnauthorized: false });

encrypt(SECRET)(socketRegistry);
encrypt(SECRET)(kafkaWebSocket);

export { socketRegistry, kafkaWebSocket };