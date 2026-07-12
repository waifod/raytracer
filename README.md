# rtnya

A ray tracer in Rust, based on [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) nya~

## Usage

```
cargo run --release -- [OPTIONS] > image.ppm
```

### Options

| Flag | Description | Default |
|------|-------------|---------|
| `-w, --width` | Image width in pixels | 1200 |
| `-s, --spp` | Samples per pixel | 500 |
| `-d, --depth` | Max ray bounce depth | 50 |

### Quick test render

```
cargo run --release -- -w 400 -s 10 -d 10 > image.ppm
```
