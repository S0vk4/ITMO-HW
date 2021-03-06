use List::MoreUtils qw/ uniq /;

my $text;
while(<>) {
    $text = $text.$_;
}
$text =~ s/\n//g;
#print $text, "\n";
my @refs;
while ($text =~ /<[^<>]*?a +[^<>]*?href[^<>]*?=[^<>]*?"(\w*?:\/\/)?([^<>]*?@)?(([^.<>]+?\.?)+?)([:\/#?][^<>]*?)?"[^<>]*?>/g) {
    push(@refs, $3);
}

@refs = uniq @refs;
@refs = sort @refs;
foreach ( @refs ) {
    print $_, "\n";
}
