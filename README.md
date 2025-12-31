Binary Tree C Demo

这是一个二叉搜索树（BST）示例项目，包含：

- `tree.c`：示例代码（插入/删除/查找/遍历）。
- `Makefile`：一键构建与运行（`make run`）。
- `run.sh`：简单的构建并运行脚本。
- `.vscode/` 配置：使得在 VS Code 中按 F5 即可一键构建并运行。
- `AI_setup_prompt.txt`：把本文件内容复制给 AI，可在克隆后自动生成必要的编辑器配置。

快速使用：

```bash
make run
# 或
bash run.sh
# 在 VS Code 中按 F5
```

上传到 GitHub：参见项目根的 `AI_setup_prompt.txt` 获取详细说明。

---

## C++ 项目快速说明（笔记合并）

以下为你要求的说明（简洁版）：

1) Code 目录
- 含义：工作区根目录，用于放置多个项目或示例。
- 用途：按子目录组织不同项目，便于管理与版本控制。
- 何时使用：你开始新的练习或项目时，在 Code 下创建独立子目录。

2) 新建（创建目录/文件）
- 含义：在文件系统中创建新的文件夹或源文件。
- 用途：为新项目或示例分配独立空间，避免文件混淆。
- 何时使用：开始新项目或需要隔离实验代码时。

3) cpp-demo（子目录名示例）
- 含义：一个示例项目的文件夹名称。
- 用途：把 C++ 示例源码、构建脚本和配置放入该目录。
- 何时使用：每个独立示例或教学案例都应该放在单独子目录。

4) main.cpp
- 含义：C++ 程序入口文件，包含 int main()。
- 用途：程序执行的起点，编译后生成可执行文件。
- 何时使用：每个可执行 C++ 程序至少需要一个含 main 的源文件。

5) Makefile
- 含义：定义构建规则的文本文件（make 工具使用）。
- 用途：统一编译命令、支持增量编译、提供常用目标（all/run/clean）。
- 何时使用：项目中有多个源文件或想要一条命令完成构建时。

6) 提交到本地 git（git add / git commit）
- 含义：把改动记录到本地版本库。
- 用途：保留历史、回滚、分阶段开发。
- 何时使用：达到一个小改动后就提交，便于追踪与恢复。

7) 推送到远程（git push）
- 含义：把本地提交上传到远程仓库（如 GitHub）。
- 用途：备份、共享、触发 CI、协作。
- 何时使用：当你准备共享代码或需要远程备份时。

8) “不会推送远程，除非你需要”
- 含义：默认只在本地提交，不执行 git push。
- 用途：先在本地迭代验证再公开代码。
- 何时使用：处于早期实验、私有开发或不想公开时。

常用命令参考：
- 新建目录并进入：
	mkdir cpp-demo && cd cpp-demo
- 示例 main.cpp 编译运行：
	clang++ -g -std=c++17 main.cpp -o demo && ./demo
- 使用 Makefile：
	make        # 构建
	make run    # 构建并运行（如 Makefile 提供）
	make clean  # 清理产物
- 本地提交：
	git add . && git commit -m "Add cpp-demo"
- 单独仓库初始化（可选）：
	git init && git add . && git commit -m "Initial"

其他保存笔记的方法（可选）：
- 把内容加到项目的 README.md（方便展示在 GitHub）。
- 使用 GitHub Gist 保存便于分享的片段。
- 在仓库启用 Wiki 页面，写更长的文档。
- 使用 VS Code 的 workspace notes / 插件（如 "foam"、"bookmarks"）管理笔记。
- 使用笔记应用（Obsidian、Notion）集中管理学习笔记。

---
