# Base Erlang + Elixir image
FROM elixir

RUN apt-get update && apt-get install -y \
    git \
    build-essential \
    bash-completion \
    wget \
    curl \
    tar \
    grep \
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

# Install yazi
RUN git clone https://github.com/sxyazi/yazi.git /tmp/yazi \
    && cargo build --manifest-path /tmp/yazi/Cargo.toml --release --locked \
    && mv /tmp/yazi/target/release/ya /usr/local/bin/ya \
    && mv /tmp/yazi/target/release/yazi /usr/local/bin/yazi \
    && rm -rf /tmp/yazi

# Install lazigit
RUN set -eux; \
    LAZYGIT_VERSION=$(curl -s https://api.github.com/repos/jesseduffield/lazygit/releases/latest \
        | grep -Po '"tag_name": *"v\K[^"]*'); \
    curl -Lo lazygit.tar.gz \
        https://github.com/jesseduffield/lazygit/releases/download/v${LAZYGIT_VERSION}/lazygit_${LAZYGIT_VERSION}_Linux_x86_64.tar.gz; \
    tar xf lazygit.tar.gz lazygit; \
    install lazygit /usr/local/bin/lazygit; \
    rm -f lazygit lazygit.tar.gz

