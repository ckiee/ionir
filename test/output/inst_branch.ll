; ModuleID = 'test'
source_filename = "test"

define void @foobar() {
entry:
  br i1 true, label %if_body1, label %if_body

if_body:                                          ; preds = %entry

if_body1:                                         ; preds = %entry
}
