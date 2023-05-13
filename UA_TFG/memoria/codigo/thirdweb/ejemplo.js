import { ThirdwebStorage } from "@thirdweb-dev/storage";

// First, instantiate the SDK
const storage = new ThirdwebStorage();

// Now we can upload a file and get the upload URI
const file = readFileSync("path/to/file.jpg");
const uri = await storage.upload(file);

// Finally we can download the file data again
const res = await storage.download(uri);
const data = await res.text();