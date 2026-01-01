Mac 科研开发环境配置备忘录
1. 核心软件安装 (Homebrew)
```

# 基础科研三件套 (服务器、翻译、截图)

brew install --cask termius bob shottr

# 代码高亮预览

brew install --cask syntax-highlight

# 环境管理核心 (Miniforge)

brew install --cask miniforge

```

2. Python 环境配置 (Miniforge)
初始化与配置：

```

conda init zsh

# 重启终端后执行，取消自动激活 base

conda config --set auto_activate_base false

```

创建主力测试环境 (lab)：

```

# 创建 Python 3.10 环境

mamba create -n lab python=3.10 -y

# 激活环境

conda activate lab

# 安装 PyTorch (支持 Mac MPS 加速) 及常用库

pip install torch torchvision numpy pandas matplotlib

```

3. 日常工作流 (SOP)
1. 打开终端：界面清爽，无 `(base)`。

2. 激活环境：输入 `conda activate lab`。

3. 开发代码：

  • 打开 VS Code。

  • 右下角解释器选择：`Python 3.10.x ('lab')`。

  • 编写代码进行本地 Debug。

4. 服务器训练：

  • 代码调试通了，通过 Termius/SFTP 上传到老师服务器。

  • 在服务器上跑实验。

4. 常用 Conda 命令速查
• 进入环境：`conda activate <名字>`

• 退出环境：`conda deactivate`

• 新建环境：`mamba create -n <名字> python=<版本>`

• 删除环境：`conda remove -n <名字> --all`

• 查看环境列表：`conda env list`
