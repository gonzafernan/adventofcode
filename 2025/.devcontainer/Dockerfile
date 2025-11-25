# Base Erlang + Elixir image
FROM elixir

RUN apt-get update && apt-get install -y \
    git \
    build-essential \
    bash-completion \
    wget \
    ffmpeg 7zip jq poppler-utils fd-find ripgrep fzf zoxide imagemagick \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Install Rust toolchain
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
ENV PATH="/root/.cargo/bin:${PATH}"
RUN git clone https://github.com/sxyazi/yazi.git /tmp/yazi \
    && cargo build --manifest-path /tmp/yazi/Cargo.toml --release --locked \
    && mv /tmp/yazi/target/release/ya /usr/local/bin/ya \
    && mv /tmp/yazi/target/release/yazi /usr/local/bin/yazi \
    && rm -rf /tmp/yazi

