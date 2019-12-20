; ModuleID = 'test'
source_filename = "test"

define void @foobar() {
entry:
  br i1 true, label %ifbody, <null operand!>

ifbody:                                           ; preds = %entry
}
