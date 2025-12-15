👋 Howdy! I'm [@JohnAlexINL](https://github.com/johnalexinl)
You'll find a bunch of small widgets I've made for myself over the moons,
as well as links to bigger projects I'm working on here.

🌱 If you're looking for a dev, I always love an opportunity to do something cool.
I know C, JavaScript, BASIC, Python, Lua, a few different assemblers, and I'm teaching myself C# too!

<p align="center">
  <a href="https://skillicons.dev">
    <img src="https://skillicons.dev/icons?perline=6&i=c,git,github,vscode,windows,linux,apple,bash,androidstudio,html,css,js,nodejs,lua,python,cs,regex,bots" />
  </a><br>
  <a href="https://github.com/anuraghazra/github-readme-stats">
    <img src="https://github-readme-stats.vercel.app/api/top-langs/?username=johnalexinl&layout=pie&bg_color=151515&border_color=080808">
  </a><br>
</p>

# Blood Rose Records

❤️ I help run an indie record label! Here's a couple of our artists
- The Lithiums, ["Future If Future" (Music Video)](https://www.youtube.com/watch?v=D_K7zt8DsIo)
- INoLonger, ["Being You" (Music Video)](https://www.youtube.com/watch?v=uNR3PwMQNJs)
- Shane Something, ["Empty Actions" (Audio)](https://www.youtube.com/watch?v=EWxwVslQsDo)
- billie arc, ["Better Off" (Audio)](https://www.youtube.com/watch?v=0qItQSExrkg)

# Projects

- [🕸️ Weaver](https://bloodrose.org/weaver), tiny JavaScript webhosting library
- [✏️ nex](https://github.com/BloodRoseorg/nex), tiny terminal hex editor with a Nano-like interface

### Work-in-Progress

- [🔮 Moongin](), C+Lua Game Engine w/ lightweight 2D and 3D Support
- [🐍 Garter](https://bloodrose.org/garter), straightforward procedural programming language
- [🛠️ gasm](https://bloodrose.org/gasm), portable platform-agnostic assembler

# Style Preferences

Code should be based around and implement _interfaces_
in a way that our logic can be plugged in and out with other code
implementing that same interface.

### Code Logic

- **Avoid additional external dependencies**; if you do not _need_ it, do not _depend_ on it
- Complicated build chains mean code that is not portable and has points of failure that are hard to hunt down
- Code with less surface area is more performant, easier to maintain, and easier to extend
- Don't Repeat Yourself; reused logic should get factored out
- _Fail early_ & **_fail often_**; instead of nesting `if`s, invert the logic and _break out on failure_.
- If code needs lots of comments, it probably isn't very good code
- If code cannot be reasonably read by one single person in a single sitting, it's going to suck to maintain
- Looking at a variable's name, it should be immediately obvious what it is: a function, a number, an iterator, a string, ...
- Code being readable and logically coherent is more important than "optimizations" your compiler is going to replace anyway
- If code matter-of-factly describes what it does, documentation and commentary becomes redundant

### Libraries and APIs

- Source distribution is always preferable; blobs cannot be ported, cannot be audited, and cannot be maintained
- **Single-file** source libraries are easier to include, easier to build, and easier to ship
- Definitions and interfaces should go at the top after any copyright notice
- Implementations should go in the middle, followed at the end by the full license agreement
- Platform-specific implementation should be factored out of the API functions and interfaces themselves
- Our libraries should [do one thing and do them well](https://en.wikipedia.org/wiki/Unix_philosophy)

### Licensing and Requirements

- Short licenses are licenses that actually get read
- As much as reasonably can-be, code should be open-sourced for its own longevity and for the community good
- Subscriptions suck. I do not want to "subscribe" or pay for a "license", I want to purchase and own.
- BSD-style licenses are **_based_** because they're straightforward
- Putting code into the Public Domain is **_even more based_**

> [!IMPORTANT]
> I do not know C++. I do not want to know C++. You cannot pay me a large enough amount of money to learn C++.
> I have lived my entire life below the poverty line, and yet, if you were to offer me a literal billion dollars to learn C++, 
> I would decline, because if there is to be any one hill I must die on,
> one folly that must befell me, a "hot take" I am ok with being my ruin,
> I want it to be that I am, through-and-through, the biggest hater of C++
