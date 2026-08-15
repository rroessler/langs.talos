/// Declare Client
'use client';

/// Vendor Modules
import { useI18n } from 'fumadocs-ui/contexts/i18n';
import { useDocsSearch } from 'fumadocs-core/search/client';
import { oramaStaticClient } from 'fumadocs-core/search/client/orama-static';
import * as Prompt from 'fumadocs-ui/components/dialog/search';

/** Search Dialog Component. */
export interface Search extends Search.Props {}
export function Search(props: Search) {
    const { locale } = useI18n(); // (optional) for internationalization
    const { search, setSearch, query } = useDocsSearch({ locale, client: oramaStaticClient() });

    // construct the search dialog to be used.
    return (
        <Prompt.SearchDialog search={search} onSearchChange={setSearch} isLoading={query.isLoading} {...props}>
            <Prompt.SearchDialogOverlay />
            <Prompt.SearchDialogContent>
                <Prompt.SearchDialogHeader>
                    <Prompt.SearchDialogIcon />
                    <Prompt.SearchDialogInput />
                    <Prompt.SearchDialogClose />
                </Prompt.SearchDialogHeader>
                <Prompt.SearchDialogList items={query.data !== 'empty' ? query.data : null} />
            </Prompt.SearchDialogContent>
        </Prompt.SearchDialog>
    );
}

export namespace Search {
    //  TYPEDEFS  //

    /** Search Component Properties. */
    export type Props = Prompt.SharedProps;
}
