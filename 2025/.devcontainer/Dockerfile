# Base Erlang + Elixir image
FROM elixir

RUN apt-get update && apt-get install -y \
    git \
    build-essential \
    bash-completion \
    wget \
    ffmpeg 7zip jq poppler-utils fd-find ripgrep fzf zoxide imagemagick \
    iputils-ping \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Install ElixirLS
RUN git clone https://github.com/elixir-lsp/elixir-ls.git /opt/elixir-ls \
    && cd /opt/elixir-ls \
    && mix deps.get \
    && mix elixir_ls.release2

# Install Rust toolchain
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
ENV PATH="/root/.cargo/bin:${PATH}"

# Install Yazi
RUN git clone https://github.com/sxyazi/yazi.git /tmp/yazi \
    && cargo build --manifest-path /tmp/yazi/Cargo.toml --release --locked \
    && mv /tmp/yazi/target/release/ya /usr/local/bin/ya \
    && mv /tmp/yazi/target/release/yazi /usr/local/bin/yazi \
    && rm -rf /tmp/yazi

