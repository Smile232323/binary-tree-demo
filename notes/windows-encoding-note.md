# Windows 控制台中文乱码原因与修复

## 现象
- cmd / PowerShell 显示中文乱码（例如启动横幅中的中文变成乱码）。

## 根因
- 控制台默认代码页为 936（GBK），与 UTF-8 输出不一致。
- PowerShell profile 被执行策略阻止，导致编码设置未生效。
- cmd 默认代码页未持久化为 UTF-8。

## 修复步骤
### PowerShell
1. 允许加载当前用户 profile（执行策略）：
```powershell
Set-ExecutionPolicy -Scope CurrentUser RemoteSigned -Force
```

2. 写入 UTF-8 输入/输出编码与 code page：
```powershell
[Console]::InputEncoding = [System.Text.Encoding]::UTF8
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
chcp 65001 > $null
```

> 将上述 3 行写入 `Documents\WindowsPowerShell\profile.ps1`，新开 PowerShell 生效。

### cmd
1. 设置 AutoRun，每次打开 cmd 自动切换 code page：
```cmd
reg add "HKCU\Software\Microsoft\Command Processor" /v AutoRun /t REG_SZ /d "chcp 65001 >nul" /f
```

2. 设置默认 code page 为 UTF-8：
```cmd
reg add "HKCU\Console" /v CodePage /t REG_DWORD /d 65001 /f
```

> 新开 cmd 生效。

## 验证
- PowerShell：
```powershell
chcp
[Console]::OutputEncoding.WebName
[Console]::InputEncoding.WebName
```

- cmd：
```cmd
chcp
echo 你好
```

## 备注
- `chcp` 只能接数字代码页，不支持中文参数。
- 如果仍乱码，检查终端字体或使用 Windows Terminal。
