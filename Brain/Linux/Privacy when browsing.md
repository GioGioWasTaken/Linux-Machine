### Fingerprinting
Your machine can be identified by many means other than your IP address. Each browser has a unique fingerprint, which is gotten by the browser's visual aspects, the operating system, and so on. To avoid fingerprinting One is ought to use some form standardized browser UI, and spoof different details like the OS being used and so on.

Browser fingerprinting involves gathering information about a user's browser and device to create a unique identifier or "fingerprint." Here are some examples of techniques used in browser fingerprinting:

1. **User-Agent String**: Browsers send a User-Agent string with each HTTP request, which includes details about the browser, operating system, and device.

2. **HTTP Headers**: Other HTTP headers such as Accept-Encoding, Accept-Language, and Referer can also provide information about the user's preferences and browsing habits.

3. **JavaScript APIs**: Browsers expose various JavaScript APIs that can be used to gather information about the user's device, such as screen resolution, installed fonts, timezone, and plugins.

4. **WebRTC IP Address Leakage**: WebRTC (Web Real-Time Communication) APIs can reveal the user's local IP address, which can be used as part of the fingerprint.

5. **Cookies and Local Storage**: Information stored in cookies and local storage can be used to identify returning users.

6. **Browser Features Detection**: Detecting browser features and capabilities, such as support for certain HTML5 APIs, can contribute to fingerprinting.

5. **Battery Status API**: Although deprecated due to privacy concerns, some browsers still support the Battery Status API, which can be used to infer information about the user's device.



### Data collection
Chrome and friends by default collect your search data. This is used to give you more accurate search results.... and to spy on you.

