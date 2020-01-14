; ModuleID = 'test'
source_filename = "test"

define void @foobar() {
entry:
  br i1 true, label %if_body, <null operand!>

if_body:                                          ; preds = %entry
}
