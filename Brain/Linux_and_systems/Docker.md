## Docker usecases
### Other than as a great way to test your application across different machines:
Docker can also be used to host web servers in containers. It is not wise at all from a security perspective to give docker files root privilages, it's also good practice to only let root edit docker files. 
#### How can other users utilize the server, than?
Well, we can use [[Systemd]]  to make the docker server run upon boot. This way, the file is completely seperated from the users who rely on it to fetch data, and we can also avoid the docker file being edited to set up malicious web servers, or to gain root access.