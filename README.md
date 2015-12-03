# Introduction
Welcome to the Easy Biometric Capture Library. This library attempts to make Fingerprint Reading easier by providing the bridge between the scanner and the software. It should be said that the fingerprint reader needs to be Microsoft Biometrics API compliant in order to make use of this library. This library is provided as-is and we (Kasper Laursen and Mads Soenderstrup) provide no warrant of any kind or promise to support further than what we see fit. We will of course do what we can to make the library as easy to use as possible and the various bugs and errors that prevents the library from running.

## Motivation
We have been looking around for a library to use with fingerprint scanners (the P5100 from Zvetcobiometrics to be exact) and found that there were only a few proprietary ones. The problems with these were:
- Tried to be too many things at once
- Too complicated to work with for simple tasks
- Expensive licensing schemes
- Poor Documentation
- Little SDK access

So to get around this we vouced for trying to make Microsofts default API work instead so we could access our scanner through that. The only problem being none of knows C++ so we had to learn that, but Microsofts examples have been plenty fine to make us able to make a small bridge between C++ and C#.

## Licensing
We have released this library under the LGPL (GNU Lesser Public License) which in short terms means:
- You can use it for Commercial Projects
- You can use it for Private Projects
- You can sell the code with your software

**If you change the library code in any way, you have to make that code public.** This is important to keep the code free and unstrestricted from proprietary software so that everyone got a shot at developing their own bindings and versions to suit their needs. It's also just nice in general for the community so that everyone can benefit from the improvements. **You are not required to publish any of the code that is not part of this library.**

## How To Use It
TBD
