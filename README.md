<p align="center">
  <img src="resources/zephyr_icon.png" />
</p>

# zephyr

zephy is a C++ thread-per-core library that provides asynchronous I/O primitives and synchronization tools for building high-performance network applications.

Key features:
- Asynchronous I/O with io_uring
- Futures, coroutines and observables
- Synchronization primitives like mutexes and semaphores
- TCP networking - clients, servers, streams
- Timers and async signal handling
- AF_XDP support for high speed packet processing
`zephyr` applications center around an event loop which drives asynchronous logic:

```cpp
ze::event_loop loop;

auto xdp = ze::af_xdp_socket("eth0");
xdp.attach_bpf("filter.o");

while (true) {
    auto [pkt, meta] = co_await xdp.recv();
    
    // process packet
    
    co_await xdp.send(pkt);
}
```

The AF_XDP socket and BPF integration allows building high performance network functions like load balancers, firewalls, NATs etc without kernel involvement.

`zephyr` provides the core asynchronous infrastructure to leverage modern Linux features like io_uring, eBPF, AF_XDP for constructing fast and scalable network services in C++20.

# Ideas
- [ ] Use tracy for performance handling?

## Credits
- [Issue in zig repository for event loop redesign](https://github.com/ziglang/zig/issues/8224)
- [A Programmer-Friendly I/O Abstraction Over io_uring and kqueue](https://tigerbeetle.com/blog/a-friendly-abstraction-over-iouring-and-kqueue/)
- [⭐ AF_XDP in Glommio](https://github.com/bryandmc/glommio/blob/xdp/XDP.md)
- 