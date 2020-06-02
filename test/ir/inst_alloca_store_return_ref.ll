; ModuleID = 'test'
source_filename = "test"

define void @foobar() {
entry:
  %foo = alloca i32
  store i32 1, i32* %foo
  ret i32* %foo
}
