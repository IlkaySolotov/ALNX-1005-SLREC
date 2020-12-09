# ALNX-1005-SLREC
Slui Handler Hijack

```yaml
TargetOS: Win10
TestedOn: 2004 SO 19041.685
Payload: Bin/Dir-Payload
Language: C++
Patch: n/a
Danger: 9
Classification: ALNX-1005-SLREC
```

**_ReTree_**
```
HKEY_CURRENT_USER
  Software
    Classes
      exefile
        shell
          open
             command
              @=Payload
```
