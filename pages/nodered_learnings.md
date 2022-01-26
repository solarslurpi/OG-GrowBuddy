# Sending gmail
The node-red flow responsible for determining when the LED lights go on/off sends an email when this event occurs. To get email to work, an [`App Password`](https://support.google.com/mail/answer/185833?hl=en) from Google needs to be used.  If not, the debug channel will give this error message:
```
Error: Invalid login: 534-5.7.9 Application-specific password required. Learn more at
534 5.7.9  https://support.google.com/mail/?p=InvalidSecondFactor f12sm11906507pfe.204 - gsmtp
```
# Installing Grafana
The last time I tried to install Grafana on Raspberry Pi (Buster) I got:
```
E: Package 'grafana' has no installation candidate
```
To get past this:
```
sudo apt-get update --fix-missing
```
Then install Grafana with:
```
sudo apt install grafana
```

