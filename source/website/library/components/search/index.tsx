'use client';

/// Vendor Modules
import {
    SearchDialog,
    SearchDialogClose,
    SearchDialogContent,
    SearchDialogHeader,
    SearchDialogIcon,
    SearchDialogInput,
    SearchDialogList,
    SearchDialogOverlay,
    type SharedProps,
} from '@fumadocs/base-ui/components/dialog/search';
import { useDocsSearch } from 'fumadocs-core/search/client';
import { useI18n } from '@fumadocs/base-ui/contexts/i18n';

/** Search Dialog Component. */
export interface Search extends Search.Props {}
export function Search(props: Search) {
    const { locale } = useI18n(); // (optional) for i18n
    const { search, setSearch, query } = useDocsSearch({ locale, type: 'static' });

    // construct the search dialog to be used.
    return (
        <SearchDialog search={search} onSearchChange={setSearch} isLoading={query.isLoading} {...props}>
            <SearchDialogOverlay />
            <SearchDialogContent>
                <SearchDialogHeader>
                    <SearchDialogIcon />
                    <SearchDialogInput />
                    <SearchDialogClose />
                </SearchDialogHeader>
                <SearchDialogList items={query.data !== 'empty' ? query.data : null} />
            </SearchDialogContent>
        </SearchDialog>
    );
}

export namespace Search {
    //  TYPEDEFS  //

    /** Search Component Properties. */
    export type Props = SharedProps;
}
