/// Vendor Modules
import { TOCItemType } from 'fumadocs-core/toc';

/** Table-of-Contents Functionality. */
export type TOC = TOCItemType[];
export namespace TOC {
    //  PUBLIC METHODS  //

    /**
     * Handles seeding toc-items.
     * @param title                 Title to bind.
     * @param options               Override options.
     */
    export function seed(title: string, options: Partial<Omit<TOCItemType, 'title'>> = {}): TOCItemType {
        return { title, url: `#${title.toLowerCase()}`, depth: 2, ...options };
    }

    /**
     * Handles constructing non-collapsible meta pages.
     * @param key                   Key to bind.
     * @param prefix                Prefix value.
     */
    export function meta(key: string, prefix: string) {
        const path = `${prefix}/${key}/meta.json`;
        const info = { path, fullPath: 'dummy.json' };
        return { type: 'meta', path, data: { info, collapsible: false } } as const;
    }
}
